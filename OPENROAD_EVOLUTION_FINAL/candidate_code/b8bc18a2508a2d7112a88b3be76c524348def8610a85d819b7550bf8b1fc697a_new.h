// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.57555425;
  double density_weight = 0.40999576;
  double prefix_weight = 0.28933519;
  double neighborhood_weight = 0.31142401;
  double late_weight = 0.21716233;
  double critical_weight = 0.46662501;
  unsigned budget = 17;
  unsigned neighborhood = 8;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
