// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.50959458;
  double density_weight = 0.08446925;
  double prefix_weight = 0.07494291;
  double neighborhood_weight = 0.22534122;
  double late_weight = 0.19763270;
  double critical_weight = 0.38134445;
  unsigned budget = 38;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
