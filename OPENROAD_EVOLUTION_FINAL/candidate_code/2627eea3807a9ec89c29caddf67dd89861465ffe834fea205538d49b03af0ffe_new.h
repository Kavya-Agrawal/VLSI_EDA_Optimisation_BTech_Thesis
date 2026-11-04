// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30358027;
  double density_weight = 0.03623079;
  double prefix_weight = 0.14527799;
  double neighborhood_weight = 0.18079244;
  double late_weight = 0.13564731;
  double critical_weight = 0.12586999;
  unsigned budget = 37;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
