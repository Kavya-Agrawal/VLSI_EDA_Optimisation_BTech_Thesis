// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.44345917;
  double density_weight = 0.13503345;
  double prefix_weight = 0.47975964;
  double neighborhood_weight = 0.29550863;
  double late_weight = 0.03001209;
  double critical_weight = 0.48605651;
  unsigned budget = 9;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
