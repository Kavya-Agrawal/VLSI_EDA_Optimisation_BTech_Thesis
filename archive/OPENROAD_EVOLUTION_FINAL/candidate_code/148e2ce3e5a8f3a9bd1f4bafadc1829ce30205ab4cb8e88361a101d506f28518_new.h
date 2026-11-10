// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.90269177;
  double density_weight = 0.23356265;
  double prefix_weight = 0.18431977;
  double neighborhood_weight = 0.05548692;
  double late_weight = 0.02686692;
  double critical_weight = 0.07666647;
  unsigned budget = 32;
  unsigned neighborhood = 10;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
