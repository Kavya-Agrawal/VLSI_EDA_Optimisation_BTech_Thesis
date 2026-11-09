// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12508378;
  double density_weight = 0.11140430;
  double prefix_weight = 0.05308898;
  double neighborhood_weight = 0.18906633;
  double late_weight = 0.24532203;
  double critical_weight = 0.03848856;
  unsigned budget = 22;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
