// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01630355;
  double density_weight = 0.49075339;
  double prefix_weight = 0.11357807;
  double neighborhood_weight = 0.19641057;
  double late_weight = 0.06527613;
  double critical_weight = 0.44414367;
  unsigned budget = 17;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
