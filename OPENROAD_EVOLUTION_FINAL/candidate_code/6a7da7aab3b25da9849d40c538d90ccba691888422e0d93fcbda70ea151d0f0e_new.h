// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.01246278;
  double density_weight = 0.45881316;
  double prefix_weight = 0.24186255;
  double neighborhood_weight = 0.23330394;
  double late_weight = 0.17918262;
  double critical_weight = 0.18718604;
  unsigned budget = 26;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
