// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.33671697;
  double density_weight = 0.59079917;
  double prefix_weight = 0.16488089;
  double neighborhood_weight = 0.34542837;
  double late_weight = 0.19116322;
  double critical_weight = 0.24412988;
  unsigned budget = 39;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
