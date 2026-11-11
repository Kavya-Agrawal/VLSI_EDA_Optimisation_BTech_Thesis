// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.64644404;
  double density_weight = 0.19881543;
  double prefix_weight = 0.38863964;
  double neighborhood_weight = 0.12942145;
  double late_weight = 0.09003153;
  double critical_weight = 0.23433323;
  unsigned budget = 24;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
