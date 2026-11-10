// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32131016;
  double density_weight = 0.32727849;
  double prefix_weight = 0.22824872;
  double neighborhood_weight = 0.12676924;
  double late_weight = 0.11314147;
  double critical_weight = 0.46928102;
  unsigned budget = 6;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
