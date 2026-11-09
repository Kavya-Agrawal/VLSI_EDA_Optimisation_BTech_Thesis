// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.38436302;
  double density_weight = 0.12562556;
  double prefix_weight = 0.12661211;
  double neighborhood_weight = 0.08831143;
  double late_weight = 0.21077402;
  double critical_weight = 0.14875203;
  unsigned budget = 26;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 2;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
