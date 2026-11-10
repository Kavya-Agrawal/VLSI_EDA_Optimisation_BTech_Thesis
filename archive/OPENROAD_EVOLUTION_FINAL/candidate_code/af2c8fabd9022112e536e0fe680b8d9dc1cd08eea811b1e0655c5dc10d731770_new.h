// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23795639;
  double density_weight = 0.51485359;
  double prefix_weight = 0.21612542;
  double neighborhood_weight = 0.37492434;
  double late_weight = 0.29106538;
  double critical_weight = 0.19899115;
  unsigned budget = 37;
  unsigned neighborhood = 14;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
