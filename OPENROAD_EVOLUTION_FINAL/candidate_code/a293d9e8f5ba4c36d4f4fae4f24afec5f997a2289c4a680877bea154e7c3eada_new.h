// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.34947022;
  double density_weight = 0.37541418;
  double prefix_weight = 0.33777373;
  double neighborhood_weight = 0.39861796;
  double late_weight = 0.07958087;
  double critical_weight = 0.31232324;
  unsigned budget = 7;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
