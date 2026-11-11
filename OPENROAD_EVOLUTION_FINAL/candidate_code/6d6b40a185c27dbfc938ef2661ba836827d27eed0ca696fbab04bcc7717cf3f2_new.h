// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.45776587;
  double density_weight = 0.29462580;
  double prefix_weight = 0.12154116;
  double neighborhood_weight = 0.38447702;
  double late_weight = 0.16379636;
  double critical_weight = 0.49202752;
  unsigned budget = 19;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
