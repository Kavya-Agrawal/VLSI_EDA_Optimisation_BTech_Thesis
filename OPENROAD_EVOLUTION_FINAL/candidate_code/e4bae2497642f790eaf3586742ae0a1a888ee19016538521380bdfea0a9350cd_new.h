// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.62494061;
  double density_weight = 0.46377817;
  double prefix_weight = 0.18118584;
  double neighborhood_weight = 0.07268699;
  double late_weight = 0.14426394;
  double critical_weight = 0.44547619;
  unsigned budget = 36;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
