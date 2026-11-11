// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.97443297;
  double density_weight = 0.32431508;
  double prefix_weight = 0.25983161;
  double neighborhood_weight = 0.29348984;
  double late_weight = 0.25801627;
  double critical_weight = 0.12033150;
  unsigned budget = 13;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
