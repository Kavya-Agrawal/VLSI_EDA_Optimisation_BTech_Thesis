// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.14604505;
  double density_weight = 0.48679100;
  double prefix_weight = 0.22239945;
  double neighborhood_weight = 0.38512853;
  double late_weight = 0.10608259;
  double critical_weight = 0.40220369;
  unsigned budget = 10;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
