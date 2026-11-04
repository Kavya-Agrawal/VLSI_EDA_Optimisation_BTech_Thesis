// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01332808;
  double density_weight = 0.10227926;
  double prefix_weight = 0.41421048;
  double neighborhood_weight = 0.20768800;
  double late_weight = 0.28932066;
  double critical_weight = 0.14257423;
  unsigned budget = 29;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
