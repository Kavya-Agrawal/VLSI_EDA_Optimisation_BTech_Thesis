// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.25169593;
  double density_weight = 0.27203198;
  double prefix_weight = 0.33488845;
  double neighborhood_weight = 0.03294121;
  double late_weight = 0.18050459;
  double critical_weight = 0.11393101;
  unsigned budget = 8;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
