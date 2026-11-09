// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.03098783;
  double density_weight = 0.31155082;
  double prefix_weight = 0.30523515;
  double neighborhood_weight = 0.13673877;
  double late_weight = 0.00085107;
  double critical_weight = 0.19028723;
  unsigned budget = 35;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
