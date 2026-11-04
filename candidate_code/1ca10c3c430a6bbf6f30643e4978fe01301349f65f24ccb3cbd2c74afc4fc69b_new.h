// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.59175181;
  double density_weight = 0.39479258;
  double prefix_weight = 0.41966652;
  double neighborhood_weight = 0.31957422;
  double late_weight = 0.28176017;
  double critical_weight = 0.28306555;
  unsigned budget = 10;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
