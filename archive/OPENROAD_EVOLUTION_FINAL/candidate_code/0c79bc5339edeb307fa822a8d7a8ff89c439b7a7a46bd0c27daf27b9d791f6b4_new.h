// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.82971606;
  double density_weight = 0.12027442;
  double prefix_weight = 0.34084313;
  double neighborhood_weight = 0.03284390;
  double late_weight = 0.08843042;
  double critical_weight = 0.14688668;
  unsigned budget = 20;
  unsigned neighborhood = 11;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
