// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.98317552;
  double density_weight = 0.35248272;
  double prefix_weight = 0.46538405;
  double neighborhood_weight = 0.17611519;
  double late_weight = 0.17539206;
  double critical_weight = 0.41647229;
  unsigned budget = 8;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
