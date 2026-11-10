// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.22237621;
  double density_weight = 0.17098903;
  double prefix_weight = 0.42465400;
  double neighborhood_weight = 0.11944749;
  double late_weight = 0.29106587;
  double critical_weight = 0.42146430;
  unsigned budget = 39;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
