// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.11808938;
  double density_weight = 0.07966547;
  double prefix_weight = 0.23344900;
  double neighborhood_weight = 0.18438120;
  double late_weight = 0.12585669;
  double critical_weight = 0.15527146;
  unsigned budget = 29;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
