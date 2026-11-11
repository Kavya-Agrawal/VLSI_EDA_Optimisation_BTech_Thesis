// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33892221;
  double density_weight = 0.16780497;
  double prefix_weight = 0.30729435;
  double neighborhood_weight = 0.11703692;
  double late_weight = 0.27227101;
  double critical_weight = 0.24799335;
  unsigned budget = 39;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
