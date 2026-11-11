// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.77196662;
  double density_weight = 0.24733815;
  double prefix_weight = 0.16146012;
  double neighborhood_weight = 0.16809094;
  double late_weight = 0.17412979;
  double critical_weight = 0.16968630;
  unsigned budget = 20;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
