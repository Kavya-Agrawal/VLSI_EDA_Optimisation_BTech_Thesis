// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45156819;
  double density_weight = 0.20434791;
  double prefix_weight = 0.37545100;
  double neighborhood_weight = 0.35126069;
  double late_weight = 0.14050093;
  double critical_weight = 0.37403102;
  unsigned budget = 20;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
