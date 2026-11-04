// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.08910485;
  double density_weight = 0.59102257;
  double prefix_weight = 0.29719410;
  double neighborhood_weight = 0.04730800;
  double late_weight = 0.07404480;
  double critical_weight = 0.41263029;
  unsigned budget = 27;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
