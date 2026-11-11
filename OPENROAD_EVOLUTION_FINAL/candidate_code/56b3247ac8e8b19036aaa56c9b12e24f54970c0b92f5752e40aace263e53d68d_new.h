// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25142222;
  double density_weight = 0.03244768;
  double prefix_weight = 0.48728829;
  double neighborhood_weight = 0.21292313;
  double late_weight = 0.00540781;
  double critical_weight = 0.27262387;
  unsigned budget = 38;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
