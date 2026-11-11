// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46880060;
  double density_weight = 0.38366086;
  double prefix_weight = 0.23484898;
  double neighborhood_weight = 0.09935268;
  double late_weight = 0.18808309;
  double critical_weight = 0.26037260;
  unsigned budget = 16;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
