// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.92226732;
  double density_weight = 0.22131048;
  double prefix_weight = 0.23917253;
  double neighborhood_weight = 0.20644688;
  double late_weight = 0.16424488;
  double critical_weight = 0.45030025;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
