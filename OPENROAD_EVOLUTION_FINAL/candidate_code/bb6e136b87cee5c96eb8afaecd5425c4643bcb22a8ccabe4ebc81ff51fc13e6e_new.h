// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84499162;
  double density_weight = 0.54477274;
  double prefix_weight = 0.00716381;
  double neighborhood_weight = 0.27027336;
  double late_weight = 0.13662567;
  double critical_weight = 0.06477472;
  unsigned budget = 34;
  unsigned neighborhood = 9;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
