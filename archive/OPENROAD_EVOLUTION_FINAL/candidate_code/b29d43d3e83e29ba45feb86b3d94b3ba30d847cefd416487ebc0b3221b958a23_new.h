// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82590521;
  double density_weight = 0.56809846;
  double prefix_weight = 0.12549988;
  double neighborhood_weight = 0.13730034;
  double late_weight = 0.12674951;
  double critical_weight = 0.28189631;
  unsigned budget = 13;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
