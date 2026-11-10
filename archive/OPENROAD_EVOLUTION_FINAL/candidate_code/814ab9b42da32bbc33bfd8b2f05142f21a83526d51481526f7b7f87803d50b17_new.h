// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24585875;
  double density_weight = 0.16380456;
  double prefix_weight = 0.12765869;
  double neighborhood_weight = 0.08081550;
  double late_weight = 0.01712770;
  double critical_weight = 0.22320163;
  unsigned budget = 37;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
