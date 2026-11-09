// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78609538;
  double density_weight = 0.56692759;
  double prefix_weight = 0.28290667;
  double neighborhood_weight = 0.36141040;
  double late_weight = 0.09793348;
  double critical_weight = 0.35229821;
  unsigned budget = 7;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
