// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99657280;
  double density_weight = 0.55572789;
  double prefix_weight = 0.16778926;
  double neighborhood_weight = 0.11752691;
  double late_weight = 0.03839222;
  double critical_weight = 0.26985555;
  unsigned budget = 21;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
