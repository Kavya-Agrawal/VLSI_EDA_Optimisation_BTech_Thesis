// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50817647;
  double density_weight = 0.24158277;
  double prefix_weight = 0.40339955;
  double neighborhood_weight = 0.20043966;
  double late_weight = 0.12697064;
  double critical_weight = 0.42830346;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
