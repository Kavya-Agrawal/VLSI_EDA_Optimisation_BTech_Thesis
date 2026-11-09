// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.55010260;
  double density_weight = 0.11704737;
  double prefix_weight = 0.45406814;
  double neighborhood_weight = 0.11971848;
  double late_weight = 0.16639742;
  double critical_weight = 0.39840935;
  unsigned budget = 19;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
