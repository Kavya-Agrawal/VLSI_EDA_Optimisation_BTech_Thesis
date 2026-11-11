// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.12719871;
  double density_weight = 0.55548279;
  double prefix_weight = 0.23493768;
  double neighborhood_weight = 0.25455060;
  double late_weight = 0.11817490;
  double critical_weight = 0.00185008;
  unsigned budget = 19;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
