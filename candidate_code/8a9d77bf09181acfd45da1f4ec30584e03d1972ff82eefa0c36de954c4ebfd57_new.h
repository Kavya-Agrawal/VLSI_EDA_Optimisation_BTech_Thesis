// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.84484700;
  double density_weight = 0.19107355;
  double prefix_weight = 0.10371051;
  double neighborhood_weight = 0.11283015;
  double late_weight = 0.20661392;
  double critical_weight = 0.30061103;
  unsigned budget = 40;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
