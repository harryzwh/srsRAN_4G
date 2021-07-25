/**
 * Copyright 2013-2021 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#ifndef SRSRAN_TEST_PCAP_H
#define SRSRAN_TEST_PCAP_H

#if HAVE_PCAP
#include "srsran/common/mac_pcap.h"
#include "srsran/mac/mac_sch_pdu_nr.h"
static std::unique_ptr<srsran::mac_pcap> pcap_handle = nullptr;
#define PCAP_CRNTI (0x1001)
#define PCAP_TTI (666)
#endif

namespace srsran {

int write_mac_sdu_nr(const uint32_t lcid, const uint8_t* payload, const uint32_t len);

int write_rlc_am_sdu_nr(const uint32_t lcid, const uint8_t* payload, const uint32_t len)
{
#if HAVE_PCAP
  if (pcap_handle) {
    byte_buffer_t mac_sdu;
    // Add dummy RLC AM PDU header
    mac_sdu.msg[0] = 0x80;
    mac_sdu.msg[1] = 0x00;

    // Add dummy PDCP header
    mac_sdu.msg[2] = 0x00;
    mac_sdu.msg[3] = 0x00;

    mac_sdu.N_bytes = 4;
    memcpy(mac_sdu.msg + 4, payload, len);
    mac_sdu.N_bytes += len;
    return write_mac_sdu_nr(lcid, mac_sdu.msg, mac_sdu.N_bytes);
  }
#endif // HAVE_PCAP
  return SRSRAN_ERROR;
}

int write_mac_sdu_nr(const uint32_t lcid, const uint8_t* payload, const uint32_t len)
{
#if HAVE_PCAP
  if (pcap_handle) {
    byte_buffer_t          tx_buffer;
    srsran::mac_sch_pdu_nr tx_pdu;
    tx_pdu.init_tx(&tx_buffer, len + 10);
    tx_pdu.add_sdu(lcid, payload, len);
    tx_pdu.pack();
    pcap_handle->write_dl_crnti_nr(tx_buffer.msg, tx_buffer.N_bytes, PCAP_CRNTI, 0, PCAP_TTI);
    return SRSRAN_SUCCESS;
  }
#endif // HAVE_PCAP
  return SRSRAN_ERROR;
}

} // namespace srsran

#endif // SRSRAN_TEST_COMMON_H
