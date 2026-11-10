// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.19907836;
  double density_weight = 0.14531976;
  double prefix_weight = 0.27200645;
  double neighborhood_weight = 0.19884855;
  double late_weight = 0.08077484;
  double critical_weight = 0.12923176;
  unsigned budget = 12;
  unsigned neighborhood = 15;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
