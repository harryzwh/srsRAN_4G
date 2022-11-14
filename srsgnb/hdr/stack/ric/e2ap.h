/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2022 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 *
 */

#include "srsran/asn1/e2ap.h"
#include "srsran/srsran.h"

#ifndef RIC_E2AP_H
#define RIC_E2AP_H

using namespace asn1::e2ap;

class e2ap
{
public:
  e2_ap_pdu_c generate_setup_request();
  int         process_setup_response();
  int         process_setup_failure();
  int         process_subscription_request();
  int         generate_subscription_response();
  int         generate_subscription_failure();
  int         generate_indication();

private:
};

#endif /* RIC_E2AP_H */
