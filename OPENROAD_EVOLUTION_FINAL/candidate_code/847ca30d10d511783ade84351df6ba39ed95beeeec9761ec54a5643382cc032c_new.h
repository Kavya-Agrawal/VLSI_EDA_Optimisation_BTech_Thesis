// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30974234;
  double density_weight = 0.01450219;
  double prefix_weight = 0.44747200;
  double neighborhood_weight = 0.14609145;
  double late_weight = 0.06613461;
  double critical_weight = 0.32528844;
  unsigned budget = 27;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
