// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15800127;
  double density_weight = 0.33234434;
  double prefix_weight = 0.10024801;
  double neighborhood_weight = 0.36408806;
  double late_weight = 0.12341709;
  double critical_weight = 0.03637172;
  unsigned budget = 35;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
