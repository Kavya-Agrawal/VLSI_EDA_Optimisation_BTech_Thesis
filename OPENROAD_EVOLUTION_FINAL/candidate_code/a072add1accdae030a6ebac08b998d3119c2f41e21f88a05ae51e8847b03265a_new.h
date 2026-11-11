// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.31319671;
  double density_weight = 0.39844274;
  double prefix_weight = 0.37305254;
  double neighborhood_weight = 0.39543404;
  double late_weight = 0.05487699;
  double critical_weight = 0.31631045;
  unsigned budget = 17;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
