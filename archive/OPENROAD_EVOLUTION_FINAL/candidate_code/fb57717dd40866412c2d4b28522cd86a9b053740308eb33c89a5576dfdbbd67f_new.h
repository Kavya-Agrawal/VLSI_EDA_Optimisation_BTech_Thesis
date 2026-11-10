// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.46088463;
  double density_weight = 0.16400794;
  double prefix_weight = 0.14600342;
  double neighborhood_weight = 0.16896214;
  double late_weight = 0.00538079;
  double critical_weight = 0.21218430;
  unsigned budget = 39;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
