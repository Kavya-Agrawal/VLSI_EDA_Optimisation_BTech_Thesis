// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.23361192;
  double density_weight = 0.43128829;
  double prefix_weight = 0.49987704;
  double neighborhood_weight = 0.05643230;
  double late_weight = 0.11919059;
  double critical_weight = 0.26573636;
  unsigned budget = 5;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
