// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.43088106;
  double density_weight = 0.04581830;
  double prefix_weight = 0.35694582;
  double neighborhood_weight = 0.18840608;
  double late_weight = 0.22014635;
  double critical_weight = 0.25180352;
  unsigned budget = 36;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
