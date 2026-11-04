// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.30102382;
  double density_weight = 0.48124514;
  double prefix_weight = 0.47216483;
  double neighborhood_weight = 0.35939296;
  double late_weight = 0.17360317;
  double critical_weight = 0.08144864;
  unsigned budget = 12;
  unsigned neighborhood = 13;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
