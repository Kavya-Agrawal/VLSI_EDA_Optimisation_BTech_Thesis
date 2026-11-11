// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.54698594;
  double density_weight = 0.55956355;
  double prefix_weight = 0.42842995;
  double neighborhood_weight = 0.29066462;
  double late_weight = 0.02822794;
  double critical_weight = 0.28196880;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
