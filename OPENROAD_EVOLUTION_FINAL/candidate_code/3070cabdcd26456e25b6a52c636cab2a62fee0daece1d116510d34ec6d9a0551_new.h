// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.20576984;
  double density_weight = 0.51977872;
  double prefix_weight = 0.44147138;
  double neighborhood_weight = 0.15475476;
  double late_weight = 0.17472080;
  double critical_weight = 0.07449316;
  unsigned budget = 34;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
