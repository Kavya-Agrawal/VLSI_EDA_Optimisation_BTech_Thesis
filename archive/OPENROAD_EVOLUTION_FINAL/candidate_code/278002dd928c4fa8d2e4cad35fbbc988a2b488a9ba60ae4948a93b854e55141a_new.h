// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.41465739;
  double density_weight = 0.09831679;
  double prefix_weight = 0.31881669;
  double neighborhood_weight = 0.36969279;
  double late_weight = 0.26977949;
  double critical_weight = 0.06391108;
  unsigned budget = 26;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
