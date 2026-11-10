// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62603803;
  double density_weight = 0.11512066;
  double prefix_weight = 0.39997814;
  double neighborhood_weight = 0.39168273;
  double late_weight = 0.17398062;
  double critical_weight = 0.44477656;
  unsigned budget = 19;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
