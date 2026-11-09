// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84002473;
  double density_weight = 0.30389173;
  double prefix_weight = 0.13712386;
  double neighborhood_weight = 0.19447013;
  double late_weight = 0.10808900;
  double critical_weight = 0.38863485;
  unsigned budget = 34;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
