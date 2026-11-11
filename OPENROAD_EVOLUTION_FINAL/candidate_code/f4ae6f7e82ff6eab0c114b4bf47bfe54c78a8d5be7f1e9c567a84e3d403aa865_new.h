// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.02649133;
  double density_weight = 0.09889315;
  double prefix_weight = 0.25695092;
  double neighborhood_weight = 0.23837047;
  double late_weight = 0.12747205;
  double critical_weight = 0.29757954;
  unsigned budget = 33;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
